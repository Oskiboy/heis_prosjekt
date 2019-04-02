pipeline {
    agent { 
        dockerfile {
            filename 'Dockerfile'
            dir 'Docker'
        }
    }
    stages {
        stage('Initialization') {
            steps {
                sh """
                mkdir logs
                echo "Logs Initialized" >> logs/test.log
                git submodule init
                git submodule update
                """
            }
        }
        stage('Build') {
            steps {
                sh '''
                echo "Starting build..."
                make

                '''
                sh 'echo "Build complete..."'
            }
        }
        stage('UnitTests') {
            steps {
                sh 'echo "Running Unit Tests:"'
                sh 'make tests'
                sh 'echo "Tests built successfully"'
                sh 'make run_tests >> logs/test.log' 
            }
        }
    }
    post {
        success {
            sh '''
            echo "Build passed!"
            '''
        }
        failure {
            sh '''
            echo "Build failed!"
            '''
        }
        always {
            archiveArtifacts artifacts: "logs/*.log, build/heis"
            sh '''
            ls
            echo "Starting clean"
            make clean
            rm -rf build/ logs/
            '''
        }
    }
}
